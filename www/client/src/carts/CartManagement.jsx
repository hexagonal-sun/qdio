import React from 'react';
import axios from 'axios';
import CartWallPicker from './CartWallPicker';
import CartWallEditor from './CartWallEditor';
import { Container, Breadcrumb } from 'react-bootstrap';

class CartManagement extends React.Component
{
    state = {
        cartWallId: null,
        isLoading: true,
        cartWalls: null,
        activeCartWall: null,
    };

    componentDidMount = async () => {
        const response = await axios.get('/carts/getCartWalls');

        this.setState({
            isLoading: false,
            cartWalls: response.data
        });
    }

    handleChooseCartWall = cartWall => {
        this.setState({
            activeCartWall: cartWall
        });
    }

    clearChoosenCart = () => {
        this.setState({
            activeCartWall: null,
        });
    }

    render = () => {
        let content;
        let bcItem;

        if (this.state.activeCartWall) {
            content = <CartWallEditor cartWall={this.state.activeCartWall} />;
            bcItem = <Breadcrumb.Item active>{this.state.activeCartWall.name}</Breadcrumb.Item>;
        } else
            content = <CartWallPicker onChooseCartWall={this.handleChooseCartWall} cartWalls={this.state.cartWalls} />;

        return (
            <>
              <h1>Cart Management</h1>
              <Breadcrumb>
                <Breadcrumb.Item onClick={this.clearChoosenCart} active={!this.state.activeCartWall}>Cart Wall Selection</Breadcrumb.Item>
                {bcItem}
              </Breadcrumb>
              <Container>
                {content}
              </Container>
            </>
        );
    }
}

export default CartManagement;
