import { MikroORM } from "@mikro-orm/core";
import { COOKIE_NAME, __prod__ } from "./constants";
import mikroOrmConfig from "./mikro-orm.config";
import express from "express";
import { ApolloServer } from "apollo-server-express";
import { buildSchema } from "type-graphql";
import { HelloResolver } from "./resolvers/hello";
import { ApolloServerPluginLandingPageGraphQLPlayground } from "apollo-server-core";
import { PostsResolver } from "./resolvers/posts";
import { UserResolver } from "./resolvers/user";
import session from "express-session";
import cors from "cors";
import {User} from "./entities/User";


var RedisStore = require("connect-redis")(session);


const main = async () => {
	const orm = await MikroORM.init(mikroOrmConfig);
	await orm.em.nativeDelete(User, {})
	await orm.getMigrator().up();

	const app = express();
	const redis = require("redis");

	app.use(
		cors({
			origin: "http://localhost:3000",
			credentials: true,
		})
	);

	app.use(
		session({
			name: COOKIE_NAME,
			store: new RedisStore({
				client: redis,
				disableTouch: true,
			}),
			cookie: {
				maxAge: 1000 * 60 * 60 * 24 * 365 * 10,
				httpOnly: true,
				secure: __prod__,
				sameSite: "lax",
			},
			secret: "fdhbfdbsahfbahdsbfhsdabhfbgasdg",
			saveUninitialized: false,
			resave: false,
		})
	);

	const apolloServer = new ApolloServer({
		schema: await buildSchema({
			resolvers: [HelloResolver, PostsResolver, UserResolver],
			validate: false,
		}),
		plugins: [
			ApolloServerPluginLandingPageGraphQLPlayground({
				// options
			}),
		],
		context: ({ req, res }) => ({ em: orm.em, req, res, redis }),
	});
	await apolloServer.start();

	apolloServer.applyMiddleware({ app, cors: false });

	app.listen(4000, () => {
		console.log("Listening on port 4000");
	});
};

main().catch((err) => console.error(err));
