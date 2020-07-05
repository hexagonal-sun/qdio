import React from 'react';
import { ICartSpecifier, ICart } from '../interfaces/carts';
import { Form } from 'react-bootstrap';
import axios from 'axios';
import 'react-h5-audio-player/lib/styles.css';
import AudioPlayer from 'react-h5-audio-player';

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
    newTitle?: string,
    newType?: number,
    newFileId?: number,
    newFileLoc?: string,
};

interface IProps
{
    cartSpec: ICartSpecifier,
    cart?: ICart,
};

export class CartEditor extends React.Component<IProps, IState>
{
    public readonly state: Readonly<IState> = {
        themes: [],
    };

    constructor(props : IProps)
    {
        super(props);

        const initialState : IState = {
            themes: [],
        };

        if (props.cart) {
            initialState.newTitle = props.cart.title;
            initialState.newType = props.cart.theme_id;
            initialState.newFileId = props.cart.file_id;
            initialState.newFileLoc = props.cart.file_location;
        }

        this.state = initialState;
    }

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
            <option key={theme.id} value={theme.id}>
                {theme.name}
            </option>
        );
    }

    private updateCartTitle(e : React.BaseSyntheticEvent)
    {
        this.setState({
            newTitle: e.currentTarget.value,
        });
    }

    private updateCartType(e : React.BaseSyntheticEvent)
    {
        console.log(e);
        this.setState({
            newType: e.currentTarget.value,
        });
    }

    render = () => {
        return (
            <Form>
                <Form.Group controlId="formCartTitle">
                    <Form.Label>Title</Form.Label>
                    <Form.Control type="text"
                                  placeholder="My Cart"
                                  value={this.state.newTitle}
                                  onChange={(e) => this.updateCartTitle(e)} />
                </Form.Group>
                <Form.Group controlId="formCartTheme">
                    <Form.Label>Type</Form.Label>
                    <Form.Control as="select"
                                  value={this.state.newType}
                                  onChange={(e) => this.updateCartType(e)} >
                        {this.renderThemeChoices(this.state.themes)}
                    </Form.Control>
                </Form.Group>
                <Form.Group controlId="formCartPreview">
                    <Form.Label>Preview</Form.Label>
                      <AudioPlayer
                          customVolumeControls={[]}
                          customAdditionalControls={[]}
                          src={this.state.newFileLoc} />
                </Form.Group>
            </Form>
        );
    }
}
