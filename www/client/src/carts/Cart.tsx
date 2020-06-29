import React from 'react';
import { CSSProperties } from 'react';
import { Col } from 'react-bootstrap';
import { ICart } from '../interfaces/carts';

interface IProps
{
    x : number,
    isLoading : boolean,
    cart : ICart | null,
};

export class Cart extends React.Component<IProps>
{
    render = () => {
        let cartText = "Empty";
        let cartStyle : CSSProperties = {
            color: "grey",
            borderColor: "grey",
        };

        if (this.props.isLoading)
            cartText = "Loading";

        if (this.props.cart) {
            cartText = this.props.cart.title;
            cartStyle = {
                color: this.props.cart.text_colour,
                borderColor: "black",
                backgroundColor: this.props.cart.bg_colour,
            };
        }

        return (
            <Col className="cartCell text-center" style={cartStyle}>
                {cartText}
            </Col>
        );
    }
}
