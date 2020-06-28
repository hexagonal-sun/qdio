import React from 'react';
import { CSSProperties } from 'react';
import axios from 'axios';
import { Container, Row, Col } from 'react-bootstrap';
import './CartWallEditor.css';
import { ICartWall, ICart } from '../interfaces/carts';

interface ICartRowProps
{
    y : number,
    key : number,
    isLoading : boolean,
    cartWallState : ICart[],
};

interface ICartProps
{
    x : number,
    isLoading : boolean,
    cartRowState : ICart[]
};

let Cart = (props : ICartProps) => {
    let cartText = "Empty";
    let cartState = null;
    let cartStyle : CSSProperties = {
        color: "grey",
        borderColor: "grey",
    };

    if (props.isLoading)
        cartText = "Loading";

    if (props.cartRowState)
        cartState = props.cartRowState.find(obj => obj.x === props.x);

    if (cartState) {
        cartText = cartState.title;
        cartStyle = {
            color: cartState.text_colour,
            borderColor: "black",
            backgroundColor: cartState.bg_colour,
        };
    }

    return (
        <Col className="cartCell text-center" style={cartStyle}>
          {cartText}
        </Col>
    );
};

let CartRow = (props : ICartRowProps) => {
    let cartRowState : ICart[] = [];

    if (props.cartWallState)
        cartRowState = props.cartWallState.filter(obj => obj.y === props.y);

    let carts = Array.from(Array(5)).map((x, i) => <Cart x={i}
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
        const cartRows = Array.from(Array(4)).map((x, i) => <CartRow y={i}
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
