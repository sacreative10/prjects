import { UsernamePasswordInput } from "../resolvers/UsernamePasswordInput";

export const validateRegister = (options: UsernamePasswordInput) => {
	if (options.username.length <= 2) {
		return [
			{
				field: "username",
				message: "username must be at least 3 characters",
			},
		];
	}
	if (options.username.length <= 2) {
		return [
			{
				field: "username",
				message: "username must be at least 3 characters",
			},
		];
	}

	if (!options.email.includes("@")) {
		return [
			{
				field: "email",
				message: "email must be valid",
			},
		];
	}

	if (options.password.length <= 3) {
		return [
			{
				field: "password",
				message: "password must be at least 4 characters",
			},
		];
	}

	if (options.username.includes("@")) {
		return [
			{
				field: "username",
				message: "sorry, because of our lackluster development, you cannot have @ in your username",
			},
		];
	}
	return null;
};
