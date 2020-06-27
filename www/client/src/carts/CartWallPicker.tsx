import React from 'react';
import { ListGroup } from 'react-bootstrap';

class CartWallPicker extends React.Component
{
    render = () =>
    {
        if (!this.props.cartWalls)
            return <></>;

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
