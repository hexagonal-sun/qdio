import React from 'react';
import { Navbar, Nav, Container, Row } from 'react-bootstrap';
import { Home, Music, Square } from 'react-feather';
import Overview from './Overview';
import AudioLibrary from './AudioLibrary';
import CartManagement from './carts/CartManagement';
import './Dashboard.css';

let QdioNavItem = props => {
    let icon = React.cloneElement(props.icon, {className: 'feather'});
    return (
        <Nav.Item as="li">
          <Nav.Link style={{paddingLeft: 16 + "px"}} eventKey={props.viewKey}>
            {icon}{props.linkText}
          </Nav.Link>
        </Nav.Item>
    );
};

class Dashboard extends React.Component
{
    views = [
        {key: "overview", view: <Overview />},
        {key: "audioLibrary", view: <AudioLibrary />},
        {key: "cartManagement", view: <CartManagement />},
    ];

    state = {
        currentView: this.views[0],
    };

    handleNavSelect = viewKey => {
        this.setState({
            currentView: this.views.find(obj => obj.key === viewKey),
        });
    };


    render = () => {
        return (
            <>
              <Navbar variant="dark" bg="dark" className="justify-content-between" sticky="top">
                <Navbar.Brand >Qdio Dashboard</Navbar.Brand>
                <Nav className="justify-content-end">
                  <Nav.Link onClick={this.props.onDeAuth}>Sign Out</Nav.Link>
                </Nav>
              </Navbar>

              <Container fluid={true}>
                <Row>
                  <Navbar bg="light" className="sidebar col-md-2 d-none d-md-block ">
                    <div className="sidebar-sticky">
                      <Nav className="flex-column"
                           activeKey={this.state.currentView.key}
                           onSelect={e => this.handleNavSelect(e)}
                           as="ul">
                        <QdioNavItem icon={<Home />} viewKey={this.views[0].key} linkText="Overview"/>
                        <QdioNavItem icon={<Music />} viewKey={this.views[1].key} linkText="Audio Library"/>
                        <QdioNavItem icon={<Square />} viewKey={this.views[2].key} linkText="Cart Management"/>
                      </Nav>
                    </div>
                  </Navbar>
                  <main className="col-md-9 ml-sm-auto col-lg-10 pt-3 px-4">
                    {this.state.currentView.view}
                  </main>
                </Row>
              </Container>
            </>
        );
    }
}

export default Dashboard;
