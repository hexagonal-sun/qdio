import React from 'react';
import axios from 'axios';
import { Container, Row, Col } from 'react-bootstrap';
import './CartWallEditor.css';

let Cart = props => {
    let cartText = "Empty";
    let cartState = null;
    let cartStyle = {
        color: "grey",
        borderColor: "grey"
    };

    if (props.isLoading)
        cartText = "Loading";

    if (props.cartRowState)
        cartState = props.cartRowState.find(obj => obj.x === props.x);

    if (cartState) {
        cartText = cartState.title;
        cartStyle.color = cartState.text_colour;
        cartStyle.borderColor = "black";
        cartStyle.backgroundColor = cartState.bg_colour;
    }

    return (
        <Col className="cartCell text-center" style={cartStyle}>
          {cartText}
        </Col>
    );
};

let CartRow = props => {
    let cartRowState = null;

    if (props.cartWallState)
        cartRowState = props.cartWallState.filter(obj => obj.y === props.y);

    let carts = Array.from(Array(5)).map((x, i) => <Cart x={i}
                                                         key={i}
                                                         y={props.y}
                                                         isLoading={props.isLoading}
                                                         cartRowState={cartRowState}/>);

    return (
        <Row>
          {carts}
        </Row>
    );
};

class CartWallEditor extends React.Component
{
    state = {
        isLoading: true,
        cartWallState: null,
    };

    componentDidMount = async () => {
        const response = await axios.get('/carts/getCarts/' + this.props.cartWall.id);

        this.setState({
            isLoading: false,
            cartWallState: response.data
        });
    };

    render = () => {
        let cartRows = Array.from(Array(4)).map((x, i) => <CartRow y={i}
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
