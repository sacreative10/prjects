"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const core_1 = require("@mikro-orm/core");
const constants_1 = require("./constants");
const mikro_orm_config_1 = __importDefault(require("./mikro-orm.config"));
const express_1 = __importDefault(require("express"));
const apollo_server_express_1 = require("apollo-server-express");
const type_graphql_1 = require("type-graphql");
const hello_1 = require("./resolvers/hello");
const apollo_server_core_1 = require("apollo-server-core");
const posts_1 = require("./resolvers/posts");
const user_1 = require("./resolvers/user");
const express_session_1 = __importDefault(require("express-session"));
const cors_1 = __importDefault(require("cors"));
const User_1 = require("./entities/User");
var RedisStore = require("connect-redis")(express_session_1.default);
const main = async () => {
    const orm = await core_1.MikroORM.init(mikro_orm_config_1.default);
    await orm.em.nativeDelete(User_1.User, {});
    await orm.getMigrator().up();
    const app = (0, express_1.default)();
    const redis = require("redis");
    app.use((0, cors_1.default)({
        origin: "http://localhost:3000",
        credentials: true,
    }));
    app.use((0, express_session_1.default)({
        name: constants_1.COOKIE_NAME,
        store: new RedisStore({
            client: redis,
            disableTouch: true,
        }),
        cookie: {
            maxAge: 1000 * 60 * 60 * 24 * 365 * 10,
            httpOnly: true,
            secure: constants_1.__prod__,
            sameSite: "lax",
        },
        secret: "fdhbfdbsahfbahdsbfhsdabhfbgasdg",
        saveUninitialized: false,
        resave: false,
    }));
    const apolloServer = new apollo_server_express_1.ApolloServer({
        schema: await (0, type_graphql_1.buildSchema)({
            resolvers: [hello_1.HelloResolver, posts_1.PostsResolver, user_1.UserResolver],
            validate: false,
        }),
        plugins: [
            (0, apollo_server_core_1.ApolloServerPluginLandingPageGraphQLPlayground)({}),
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
//# sourceMappingURL=index.js.map