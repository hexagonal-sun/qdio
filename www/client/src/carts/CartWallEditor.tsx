import React from 'react';
import { Row } from 'react-bootstrap';
import './CartWallEditor.css';
import { ICartWall } from '../interfaces/carts';
import { Cart } from './Cart';

interface ICartRowProps
{
    row : number,
    wallId: number,
};

const CartRow = (props : ICartRowProps) => {
    const carts = Array.from(Array(5)).map((_x, i) =>
        <Cart specifier={{wallId: props.wallId,
                          page: 0,
                          y: props.row,
                          x: i}}
              key={i} />);

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

class CartWallEditor extends React.Component<IProps>
{

    render = () => {
        const cartRows = Array.from(Array(4)).map((_x, i) => <CartRow row={i}
                                                                      key={i}
                                                                      wallId={this.props.cartWall.id} />);
        return (
            <>
              {cartRows}
            </>
        );
    }
}

export default CartWallEditor;
