import { Box, Button, Flex, Link } from '@chakra-ui/react';
import React from 'react';
import NextLink from 'next/link';
import { useLogoutMutation, useMeQuery } from '../generated/graphql';
import {isServer} from '../util/isServer';

interface NavbarProps {}

export const Navbar: React.FC<NavbarProps> = ({}) => {
	const [{ fetching: islogoutFetching  }, logout] = useLogoutMutation();
	const [{ data, fetching }] = useMeQuery({
		pause: isServer(),
	});
	let navbar = null;

	if (fetching) {
		navbar = null;
	} else if (!data?.me) {
		navbar = (
			<>
				<NextLink href={'/login'}>
					<Link mr={2}>Login</Link>
				</NextLink>
				<NextLink href={'/register'}>
					<Link href="login">Register</Link>
				</NextLink>
			</>
		);
	} else {
		navbar = (
			<>
				<Flex>
					<Box>Hello {data.me.username}</Box>
					<Button
						onClick={() => {
							logout();
						}}
						isLoading={islogoutFetching}
						ml={4}
						variant="link">
						Logout
					</Button>
				</Flex>
			</>
		);
	}

	return (
		<>
			<Flex bg="teal" p={4} ml={'auto'}>
				<Box ml={'auto'}>{navbar}</Box>
			</Flex>
		</>
	);
};
