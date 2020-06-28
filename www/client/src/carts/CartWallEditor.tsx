import React from 'react';
import axios from 'axios';
import { Row } from 'react-bootstrap';
import './CartWallEditor.css';
import { ICartWall, ICart } from '../interfaces/carts';
import { Cart } from './Cart';

interface ICartRowProps
{
    y : number,
    key : number,
    isLoading : boolean,
    cartWallState : ICart[],
};

let CartRow = (props : ICartRowProps) => {
    let cartRowState : ICart[] = [];

    if (props.cartWallState)
        cartRowState = props.cartWallState.filter(obj => obj.y === props.y);

    let carts = Array.from(Array(5)).map((_x, i) => <Cart x={i}
                                                          key={i}
                                                          isLoading={props.isLoading}
                                                          cartRowState={cartRowState}/>);

    return (
        <Row>
          {carts}
        </Row>
    );
};

interface IProps
{
    cartWall : ICartWall,
};

interface IState
{
    isLoading : boolean,
    cartWallState : ICart[],
};

class CartWallEditor extends React.Component<IProps, IState>
{
    state : Readonly<IState> = {
        isLoading: true,
        cartWallState: [],
    };

    componentDidMount = async () => {
        const response = await axios.get('/carts/getCarts/' + this.props.cartWall.id);

        this.setState({
            isLoading: false,
            cartWallState: response.data
        });
    };

    render = () => {
        const cartRows = Array.from(Array(4)).map((_x, i) => <CartRow y={i}
                                                                      key={i}
                                                                      isLoading={this.state.isLoading}
                                                                      cartWallState={this.state.cartWallState} />);
        return (
            <>
              {cartRows}
            </>
        );
    }
}

export default CartWallEditor;
