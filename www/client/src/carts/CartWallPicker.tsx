import React from 'react';
import { ListGroup } from 'react-bootstrap';
import { ICartWall } from '../interfaces/carts';

interface IProps 
{
    cartWalls : ICartWall[],
    onChooseCartWall : (wall : ICartWall) => void,
};

class CartWallPicker extends React.Component<IProps>
{
    render = () =>
    {
        return (
            <>
              <p>Select the cart wall you wish to edit from the list below:</p>

              <ListGroup>
                {this.props.cartWalls.map(obj =>
                      <ListGroup.Item action
                                      key={obj.name}
                                      onClick={() => this.props.onChooseCartWall(obj)} >{obj.name}</ListGroup.Item>)}
              </ListGroup>
            </>
        );
    }
}

export default CartWallPicker;
