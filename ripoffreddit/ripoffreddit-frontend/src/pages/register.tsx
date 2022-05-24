import { Box, Button } from '@chakra-ui/react';
import { Form, Formik } from 'formik';
import { withUrqlClient } from 'next-urql';
import { useRouter } from 'next/router';
import React from 'react';
import { setInterval } from 'timers';
import { InputField } from '../components/inputField';
import { Wrapper } from '../components/Wrapper';
import { useRegisterMutation } from '../generated/graphql';
import { createUrqlClient } from '../util/createUrqlClient';
import { toErrorMap } from '../util/toErrorMap';

interface RegisterProps {}

const Register: React.FC<RegisterProps> = ({}) => {
	const router = useRouter();
	const [, Register] = useRegisterMutation();
	return (
		<Wrapper variant="small">
			<Formik
				initialValues={{ username: '', password: '', email: '' }}
				onSubmit={async (values, { setErrors }) => {
					const response = await Register({ options: values });
					if (response.data?.register.errors) {
						setErrors(toErrorMap(response.data.register.errors));
					} else if (response.data?.register.user) {
						router.push('/');
					}
				}}>
				{({ isSubmitting }) => (
					<Form>
						<InputField name="username" placeholder="username" label="Username" />
						<Box mt={4}>
							<InputField name="email" placeholder="email" label="Email" type="email" />
						</Box>
						<Box mt={4}>
							<InputField name="password" placeholder="password" label="Password" type="password" />
						</Box>
						<Button mt={4} type="submit" isLoading={isSubmitting} colorScheme="teal">
							Register
						</Button>
					</Form>
				)}
			</Formik>
		</Wrapper>
	);
};

export default withUrqlClient(createUrqlClient)(Register);
