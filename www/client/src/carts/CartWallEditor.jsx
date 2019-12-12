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
        cartState = props.cartRowState.find(obj => obj.x == props.x);

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
        cartRowState = props.cartWallState.filter(obj => obj.y == props.y);

    return (
        <Row>
          <Cart x={0} y={props.y} isLoading={props.isLoading} cartRowState={cartRowState} />
          <Cart x={1} y={props.y} isLoading={props.isLoading} cartRowState={cartRowState} />
          <Cart x={2} y={props.y} isLoading={props.isLoading} cartRowState={cartRowState} />
          <Cart x={3} y={props.y} isLoading={props.isLoading} cartRowState={cartRowState} />
          <Cart x={4} y={props.y} isLoading={props.isLoading} cartRowState={cartRowState} />
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
        return (
            <>
              <CartRow y={0} isLoading={this.state.isLoading}
                       cartWallState={this.state.cartWallState} />
              <CartRow y={1} isLoading={this.state.isLoading}
                       cartWallState={this.state.cartWallState} />
              <CartRow y={2} isLoading={this.state.isLoading}
                       cartWallState={this.state.cartWallState} />
              <CartRow y={3} isLoading={this.state.isLoading}
                       cartWallState={this.state.cartWallState} />
            </>
        );
    }
}

export default CartWallEditor;
