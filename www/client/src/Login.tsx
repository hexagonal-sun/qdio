import React, { ChangeEvent, MouseEvent } from 'react';
import axios from 'axios';
import keccak from 'keccak';
import './Login.css';
import { Container, Row, Col, Form, Button, Alert } from 'react-bootstrap';
import { BrowserRouter as Router, Redirect } from 'react-router-dom';

interface State {
    signInRequested : boolean,
    isAuthenticated : boolean,
    alert : string | null,
    userName : string | null,
    password : string | null,
};

interface Props {
    onAuth : (token : string) => void,
};

class Login extends React.Component<Props, State> {

    state : Readonly<State> = {
        signInRequested: false,
        isAuthenticated: false,
        alert: null,
        userName: null,
        password: null,
    };

    handleSignInClick = async (e : MouseEvent<HTMLButtonElement>) => {
        const failMessage = 'Failed to sign in, please try again';

        e.preventDefault();

        this.setState({
            signInRequested: true,
            alert: null,
        });

        try {
            if (typeof this.state.password !== 'string')
                return;

            const findUserResponse = await axios.post('/userAuth/findUser', {
                username: this.state.userName
            });

            if (findUserResponse.status !== 200) {
                this.setState({
                    signInRequested: false,
                    alert: failMessage
                });

                return;
            }

            const hash = keccak('keccak256')
                .update(Buffer.from(findUserResponse.data['salt'], 'hex'))
                .update(this.state.password)
                .digest('hex');

            const userLoginResponse = await axios.post('/userAuth/userLogin', {
                uid: findUserResponse.data.user_id,
                hash: hash,
            });

            if (!userLoginResponse.data) {
                this.setState({
                    signInRequested: false,
                    alert: 'Invalid username or password',
                });

                return;
            }

            this.props.onAuth('0xdeadbeef');
        } catch (e) {
            console.log(e);
            this.setState({
                signInRequested: false,
                alert: failMessage,
            });
        }
    }

  handleChange = (e : ChangeEvent<HTMLInputElement>) => {
    let newState : State = {...this.state};
    const prop = e.target.name;

    if (!(prop === 'userName' || prop === 'password'))
      return

    newState[prop] = e.target.value;

    this.setState(newState);
  }

    render = () => {
        return (
            <>
              <Container style={{marginTop: "auto", marginBottom: "auto"}}>
                <Row>
                  <Col>
                    {this.state.alert &&
                     <Alert variant="danger">
                       {this.state.alert}
                     </Alert>
                    }

                    <Form id="signin-form">
                      <Form.Group controlId="signinFormEmail">
                        <Form.Label srOnly={true}>Email address</Form.Label>
                        <Form.Control disabled={this.state.signInRequested}
                                      name="userName"
                                      onChange={this.handleChange}
                                      type="input"
                                      placeholder="User Name" />
                      </Form.Group>

                      <Form.Group controlId="signinFormPassword">
                        <Form.Label srOnly={true}>Password</Form.Label>
                        <Form.Control disabled={this.state.signInRequested}
                                      name="password"
                                      onChange={this.handleChange}
                                      type="password"
                                      placeholder="Password" />
                      </Form.Group>
                      <Button variant="primary"
                              disabled={this.state.signInRequested}
                              type="submit"
                              onClick={this.state.signInRequested ? undefined : this.handleSignInClick}
                              block>
                        {this.state.signInRequested ? 'Signing In...' : 'Sign In'}
                      </Button>
                    </Form>
                    <Router>
                      {this.state.isAuthenticated && <Redirect to='/dashboard/' />}
                    </Router>
                  </Col>
                </Row>
              </Container>
            </>
        );
    }
}

export default Login;
