# base image
FROM node:12.2.0-alpine

# set working directory
WORKDIR /app

# add `/app/node_modules/.bin` to $PATH
ENV PATH /app/node_modules/.bin:$PATH

# install and cache app dependencies
COPY package.json .
RUN npm install

COPY app.ts .
COPY bin/ bin/
COPY public/ public/
COPY routes/ routes/
COPY views/ views/

# start app
CMD ["npm", "start"]
