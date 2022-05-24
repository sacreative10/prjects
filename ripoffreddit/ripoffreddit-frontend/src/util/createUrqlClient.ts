import { dedupExchange, fetchExchange } from 'urql';
import { cacheExchange } from '@urql/exchange-graphcache';
import { LoginMutation, MeDocument, MeQuery, RegisterMutation } from '../generated/graphql';
import { betterUpdateQuery } from './betterUpdateClient';

export const createUrqlClient = (ssrExchange: any) => ({
	url: 'http://localhost:4000/graphql',
	fetchOptions: { credentials: 'include' as const },
	exchanges: [
		dedupExchange,
		cacheExchange({
			updates: {
				Mutation: {
					logout(result_, args, cache, info) {
						betterUpdateQuery<LoginMutation, MeQuery>(cache, { query: MeDocument }, result_, () => ({
							me: null,
						}));
					},
					login: (result_, args, cache, info) => {
						betterUpdateQuery<LoginMutation, MeQuery>(
							cache,
							{ query: MeDocument },
							result_,
							(result, query) => {
								if (result.login?.errors) {
									return query;
								} else {
									return {
										me: result.login.user,
									};
								}
							},
						);
					},

					register: (result_, args, cache, info) => {
						betterUpdateQuery<RegisterMutation, MeQuery>(
							cache,
							{ query: MeDocument },
							result_,
							(result, query) => {
								if (result.register?.errors) {
									return query;
								} else {
									return {
										me: result.register.user,
									};
								}
							},
						);
					},
				},
			},
		}),
		ssrExchange,
		fetchExchange,
	],
});
