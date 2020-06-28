import React from 'react';
import axios from 'axios';
import CartWallPicker from './CartWallPicker';
import CartWallEditor from './CartWallEditor';
import { Container, Breadcrumb } from 'react-bootstrap';
import { ICartWall } from '../interfaces/carts';

interface IState {
    cartWallId: string | null,
    isLoading : boolean,
    cartWalls : ICartWall[],
    activeCartWall : ICartWall | null
};

class CartManagement extends React.Component
{
    state : Readonly<IState> = {
        cartWallId: null,
        isLoading: true,
        cartWalls: [],
        activeCartWall: null,
    };

    componentDidMount = async () => {
        const response = await axios.get<ICartWall[]>('/carts/getCartWalls');

        this.setState({
            isLoading: false,
            cartWalls: response.data
        });
    }

    handleChooseCartWall = (cartWall : ICartWall) => {
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
            content = <CartWallPicker onChooseCartWall={this.handleChooseCartWall}
                                      cartWalls={this.state.cartWalls} />;

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
