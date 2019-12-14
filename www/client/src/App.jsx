import React from 'react';
import 'bootstrap/dist/css/bootstrap.min.css';
import Login from './Login';
import Dashboard from './Dashboard';

class App extends React.Component
{
    state = {
        authToken: null
    }

    handleAuth = token => {
        this.setState({
            authToken: token
        });
    }

    render = () => {
        return (
            <>
              {this.state.authToken ? <Dashboard onDeAtuh={() => this.handleDeAuth()}/> :
                                      <Login onAuth={token => this.handleAuth(token)}/>}
            </>
        );
    }
}

export default App;
