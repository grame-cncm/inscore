
type TPosition 	=	{ x: number, y: number };
type TMouseEnv 	=	{ rel: TPosition, abs: TPosition, parent: TPosition };
type TSize 		=	{ w: number, h: number };
type TPair<T> 	=	{ first: T, second: T };

interface TPositionHandler  { (): TPosition; }