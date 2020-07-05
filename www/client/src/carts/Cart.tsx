import React from 'react';
import axios from 'axios';
import { CSSProperties } from 'react';
import { Col, Modal, Button } from 'react-bootstrap';
import { ICart, ICartSpecifier } from '../interfaces/carts';
import { CartEditor } from './CartEditor';

interface IProps
{
    specifier: ICartSpecifier,
};

interface IState
{
    isLoading: boolean,
    showModal : boolean,
    cart? : ICart,
};

export class Cart extends React.Component<IProps, IState>
{
    state : Readonly<IState> = {
        showModal : false,
        isLoading: true,
    };

    async componentDidMount()
    {
        try {
            const s = this.props.specifier;
            const response = await axios.get<ICart>(`/carts/${s.wallId}/${s.page}/${s.x}/${s.y}`);

            this.setState({
                isLoading: false,
                cart: response.data,
            });
        } catch(err) {
        }

        this.setState({
            isLoading: false,
        })
    }

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

        if (this.state.isLoading)
            cartText = "Loading";

        if (this.state.cart) {
            cartText = this.state.cart.title;
            cartStyle = {
                color: this.state.cart.text_colour,
                borderColor: "black",
                backgroundColor: this.state.cart.bg_colour,
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
                        <Modal.Title>Edit Cart '{this.state.cart?.title}'</Modal.Title>
                    </Modal.Header>

                    <Modal.Body>
                        <CartEditor cartSpec={this.props.specifier}
                                    cart={this.state.cart} />
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
