import React from 'react';
import { Navbar, Nav, Container, Row } from 'react-bootstrap';
import { Home, Music, Square } from 'react-feather';
import { BrowserRouter as Router, Route, Switch } from 'react-router-dom';
import Overview from './Overview';
import AudioLibrary from './AudioLibrary';
import CartManagement from './carts/CartManagement';
import './Dashboard.css';

let QdioNavItem = props => {
    let icon = React.cloneElement(props.icon, {className: 'feather'});
    let c = window.location.pathname.includes(props.href) ? 'active' : '';

    return (
        <Nav.Item as="li">
          <Nav.Link style={{paddingLeft: 16 + "px"}} className={c} href={props.href}>
            {icon}{props.linkText}
          </Nav.Link>
        </Nav.Item>
    );
};

class Dashboard extends React.Component
{
    render = () => {
        return (
            <>
              <Navbar variant="dark" bg="dark" className="justify-content-between" sticky="top">
                <Navbar.Brand >Qdio Dashboard</Navbar.Brand>
                <Nav className="justify-content-end">
                  <Nav.Link onSelect={this.props.onDeAuth}>Sign Out</Nav.Link>
                </Nav>
              </Navbar>

              <Container fluid={true}>
                <Row>
                  <Navbar bg="light" className="sidebar col-md-2 d-none d-md-block ">
                    <div className="sidebar-sticky">
                      <Nav className="flex-column" as="ul">
                        <QdioNavItem icon={<Home />} href="overview" linkText="Overview"/>
                        <QdioNavItem icon={<Music />} href="audio-library" linkText="Audio Library"/>
                        <QdioNavItem icon={<Square />} href="cart-management" linkText="Cart Management"/>
                      </Nav>
                    </div>
                  </Navbar>
                  <main className="col-md-9 ml-sm-auto col-lg-10 pt-3 px-4">
                    <Router>
                      <Switch>
                        <Route path='/dashboard/overview'>
                          <Overview/>
                        </Route>
                        <Route path='/dashboard/audio-library'>
                          <AudioLibrary/>
                        </Route>
                        <Route path='/dashboard/cart-management'>
                          <CartManagement/>
                        </Route>
                      </Switch>
                    </Router>
                  </main>
                </Row>
              </Container>
            </>
        );
    }
}

export default Dashboard;
