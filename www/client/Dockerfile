# base image
FROM node:14.4.0-alpine

# set working directory
WORKDIR /app

# add `/app/node_modules/.bin` to $PATH
ENV PATH /app/node_modules/.bin:$PATH

# install and cache app dependencies
COPY package.json .
COPY tsconfig.json .
RUN npm install

COPY public/ public/
COPY src/ src/

# start app
CMD ["npm", "start"]
