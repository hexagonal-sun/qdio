import React from 'react';
import { CSSProperties } from 'react';
import { Col, Modal, Button } from 'react-bootstrap';
import { ICart } from '../interfaces/carts';
import { CartEditor } from './CartEditor';

interface IProps
{
    x : number,
    isLoading : boolean,
    cart? : ICart,
};

interface IState
{
    showModal : boolean,
};

export class Cart extends React.Component<IProps, IState>
{
    state : Readonly<IState> = {
        showModal : false,
    };

    private handleShow()
    {
        this.setState({showModal : true});
    }

    private handleClose()
    {
        this.setState({showModal : false});
    }

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
            <>
                <Col className="cartCell text-center" style={cartStyle}
                     onClick={() => this.handleShow()}>
                    {cartText}
                </Col>
                <Modal show={this.state.showModal}>
                    <Modal.Header closeButton>
                        <Modal.Title>Edit Cart '{this.props.cart?.title}'</Modal.Title>
                    </Modal.Header>

                    <Modal.Body>
                        <CartEditor cart={this.props.cart} />
                    </Modal.Body>

                    <Modal.Footer>
                        <Button variant="secondary"
                                onClick={() => this.handleClose()}>
                            Close
                        </Button>
                        <Button variant="primary">
                            Save changes
                        </Button>
                    </Modal.Footer>
                </Modal>
            </>
        );
    }
}
