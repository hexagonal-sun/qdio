import React from 'react';
import 'bootstrap/dist/css/bootstrap.min.css';
import Login from './Login';
import Dashboard from './Dashboard';

interface State
{
    authToken : string | null
};

class App extends React.Component
{
    state : Readonly<State> = {
        authToken: null
    }

    handleAuth = (token : string) => {
        this.setState({
            authToken: token
        });
    }

    handleDeAuth = () => {
        this.setState({
            authToken: null,
        });
    }

    render = () => {
        return (
            <>
              {this.state.authToken ? <Dashboard onDeAuth={() => this.handleDeAuth()}/> :
                                      <Login onAuth={token => this.handleAuth(token)}/>}
            </>
        );
    }
}

export default App;
