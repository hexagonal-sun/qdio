import React from 'react';
import { CSSProperties } from 'react';
import { Col } from 'react-bootstrap';
import { ICart } from '../interfaces/carts';

interface IProps
{
    x : number,
    isLoading : boolean,
    cartRowState : ICart[]
};

export class Cart extends React.Component<IProps>
{
    render = () => {
        let cartText = "Empty";
        let cartState = null;
        let cartStyle : CSSProperties = {
            color: "grey",
            borderColor: "grey",
        };

        if (this.props.isLoading)
            cartText = "Loading";

        if (this.props.cartRowState)
            cartState = this.props.cartRowState.find(obj => obj.x === this.props.x);

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
    }
}
