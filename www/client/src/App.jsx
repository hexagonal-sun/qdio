import React from 'react';
import 'bootstrap/dist/css/bootstrap.min.css';
import Login from './Login';
import Dashboard from './Dashboard';
import { Route, BrowserRouter as Router, Switch, Redirect } from 'react-router-dom';

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
        let authRoute = () => {
            if (this.state.authToken)
                return <Redirect to='/dashboard'/>;
            else
                return <Login onAuth={this.handleAuth}/>;
        };

        let dashboardRoute = () => {
            if (this.state.authToken)
                return <Dashboard onDeAtuh={this.handleDeAuth} />;
            else
                return <Redirect to='/'/>;
        };

        return (
            <Router>
              <Switch>
                <Route path='/dashboard'>
                  {dashboardRoute}
                </Route>
                <Route path='/'>
                  {authRoute}
                </Route>
              </Switch>
            </Router>
        );
        return (<Dashboard/>);
    }
}

export default App;
