
///<reference path="./IMessage.ts"/>
///<reference path="../lib/TEnums.ts"/>
///<reference path="../externals/fraction.ts"/>

"use strict"

// ------------------------------------------------------------------------------
// the set message handler types
// ------------------------------------------------------------------------------
interface TSetHandler { handle(msg: IMessage): msgStatus; }

abstract class SetMsgHandler<T> implements TSetHandler { 
    protected fMethod: T;
    constructor(method: T) { this.fMethod = method; }    
	abstract handle(msg: IMessage): msgStatus;
}

interface SetMsgMethod  	{ (msg: IMessage): msgStatus; }
interface SetVoidMethod 	{ (): void; }
interface SetNumMethod 		{ (val: number): void; }
interface SetStringMethod 	{ (val: string): void; }
interface SetTimeMethod 	{ (val: Fraction): void; }
interface SetColorMethod 	{ (val: Array<number>): void; }
interface SetArrayMethod	{ (val: Array<number>): void; }

// ------------------------------------------------------------------------------
// the get message handler types
// ------------------------------------------------------------------------------
interface TGetHandler 		{ fill(msg: IMessage): IMessage; }
interface TGetMultiHandler 	{ fill(msg: IMessageList): IMessageList; }

abstract class GetMsgHandler<T> implements TGetHandler { 
    protected fMethod: T;
    constructor(method: T) { this.fMethod = method; }    
	abstract fill(msg: IMessage): IMessage;
}

interface GetNumMethod 			{ (): number; }
interface GetStringMethod 		{ (): string; }
interface GetArrayMethod 		{ (): Array<any>; }
interface GetTimeMethod 		{ (): Fraction; }