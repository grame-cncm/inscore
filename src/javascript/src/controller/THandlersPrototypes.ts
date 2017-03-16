
///<reference path="IMessage.ts"/>
///<reference path="../lib/TEnums.ts"/>
///<reference path="../externals/fraction.ts"/>

"use strict"

// ------------------------------------------------------------------------------
// the set message handler types
// ------------------------------------------------------------------------------
interface TSetHandler { handle(msg: IMessage): eMsgStatus; }

abstract class SetMsgHandler<T> implements TSetHandler { 
    protected fMethod: T;
    constructor(method: T) { this.fMethod = method; }    
	abstract handle(msg: IMessage): eMsgStatus;
}

interface SetMsgMethod  	{ (msg: IMessage): eMsgStatus; }
interface SetVoidMethod 	{ (): void; }
interface SetNumMethod 		{ (val: number): void; }
interface SetStringMethod 	{ (val: string): void; }
interface SetTimeMethod 	{ (val: Fraction): void; }
interface SetColorMethod 	{ (val: Array<number>): void; }
interface SetNumArrayMethod	{ (val: Array<number>): eMsgStatus; }
interface SetAnyArrayMethod	{ (val: Array<any>): eMsgStatus; }

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