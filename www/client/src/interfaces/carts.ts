export interface ICartWall
{
    name : string,
    id : number,
};

export interface ICartSpecifier
{
    wallId : number,
    page : number,
    x : number,
    y : number,
};

export interface ICart
{
    title: string,
    theme_id: number,
    file_id: number,
    bg_colour: string,
    text_colour: string,
    theme_name: string,
    file_location: string,
}
