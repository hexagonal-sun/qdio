import React from 'react';
import { ICart } from '../interfaces/carts';
import { Form } from 'react-bootstrap';
import axios from 'axios';

interface ICartTheme
{
    id : number,
    name : string,
    bg_colour : string,
    text_colour : string,
};

interface IState
{
    themes : ICartTheme[],
};

interface IProps
{
    cart?: ICart,
};

export class CartEditor extends React.Component<IProps, IState>
{

    state : Readonly<IState> = {
        themes : [],
    };

    async componentDidMount()
    {
        const cartThemes = await axios.get<ICartTheme[]>('/carts/themes');

        this.setState({
            themes : cartThemes.data,
        });
    }

    private renderThemeChoices(themes : ICartTheme[])
    {
        return themes.map(theme =>
            <option key={theme.id} value={theme.name}>
                {theme.name}
            </option>
        );
    }

    render = () => {
        return (
            <Form>
                <Form.Group controlId="formCartTitle">
                    <Form.Label>Title</Form.Label>
                    <Form.Control value={this.props?.cart?.title ?? ""}
                                  type="text" placeholder="My Cart" />
                </Form.Group>
                <Form.Group controlId="formCartTheme">
                    <Form.Label>Type</Form.Label>
                    <Form.Control as="select"
                                  value={this.props.cart?.theme_name}>
                        {this.renderThemeChoices(this.state.themes)}
                    </Form.Control>
                </Form.Group>
            </Form>
        );
    }
}
