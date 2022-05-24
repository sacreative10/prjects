import argon2 from "argon2";
import { MyContext } from "src/types";
import {
	Arg,
	Ctx,
	Field,
	InputType,
	Mutation,
	ObjectType,
	Query,
	Resolver,
} from "type-graphql";
import { v4 } from "uuid";

import { COOKIE_NAME, FORGET_PASSWORD_PREFIX } from "../constants";
import { User } from "../entities/User";
import { sendMail } from "../utils/sendEmail";
import { validateRegister } from "../utils/validateRegister";

@InputType()
class UsernamePasswordInput {
	@Field() username: string;

	@Field() email: string;

	@Field() password: string;
}

@ObjectType()
class FieldError {
	@Field() field: string;
	@Field() message: string;
}

@ObjectType()
class UserResponse {
	@Field(() => [FieldError], { nullable: true }) errors?: FieldError[];

	@Field(() => User, { nullable: true }) user?: User;
}

@Resolver()
export class UserResolver {
	@Mutation(() => Boolean)
	async forgotPassword(
		@Arg("email") email: string,
		@Ctx() { em, redis }: MyContext
	) {
		const user = await em.findOne(User, { email });
		if (!user) {
			// the email is not in the db

			console.log("not found");
			return true;
		}

		const token = v4();

		await redis.set(
			FORGET_PASSWORD_PREFIX + token,
			user.id,
			"ex",
			1000 * 60 * 60 * 24
		); // 1 day

		await sendMail(
			email,
			`<a href="http://localhost:3000/change-password/${token}">reset password</a>`
		);
		return true;
	}
	@Query(() => User, { nullable: true })
	async me(@Ctx() { req, em }: MyContext) {
		if (!req.session!.userId) {
			return null;
		}
		const user = await em.findOne(User, req.session!.userId);
		return user;
	}

	@Mutation(() => UserResponse)
	async register(
		@Arg("options") options: UsernamePasswordInput,
		@Ctx() { em, req }: MyContext
	): Promise<UserResponse> {
		const errors = validateRegister(options);
		if (errors) {
			return { errors };
		}

		const hash = await argon2.hash(options.password);
		const user = em.create(User, {
			username: options.username,
			password: hash,
			email: options.email,
			createdAt: new Date(),
			updatedAt: new Date(),
		});
		try {
			await em.persistAndFlush(user);
		} catch (err) {
			console.log(err);
			return {
				errors: [
					{
						field: "username",
						message: "username already exists",
					},
				],
			};
		}

		req.session!.userId = user.id;
		return { user };
	}

	@Mutation(() => UserResponse)
	async login(
		@Arg("usernameOrEmail") usernameOrEmail: string,
		@Arg("password") password: string,
		@Ctx() { em, req }: MyContext
	): Promise<UserResponse> {
		const user = await em.findOne(
			User,
			usernameOrEmail.includes("@")
				? { email: usernameOrEmail }
				: { username: usernameOrEmail }
		);
		if (!user) {
			return {
				errors: [
					{
						field: "usernameOrEmail",
						message: "that username doesn't exist",
					},
				],
			};
		}
		const valid = await argon2.verify(user.password, password);
		if (!valid) {
			return {
				errors: [
					{
						field: "password",
						message: "incorrect password",
					},
				],
			};
		}

		req.session!.userId = user.id;

		return {
			user,
		};
	}

	@Mutation(() => Boolean)
	logout(@Ctx() { req, res }: MyContext) {
		return new Promise((resolve) =>
			req?.session?.destroy((err) => {
				res.clearCookie(COOKIE_NAME);
				if (err) {
					console.log(err);
					resolve(true);
				}
				resolve(true);
			})
		);
	}
}
