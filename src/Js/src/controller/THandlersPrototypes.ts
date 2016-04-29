
///<reference path="./IMessage.ts"/>
///<reference path="../externals/fraction/fraction.ts"/>

"use strict"
enum msgStatus { 
    kBadAddress,
    kProcessed = 1,
    kProcessedNoChange = 2,
    kBadParameters = 4,
    kCreateFailure = 8,
}

// ------------------------------------------------------------------------------
// the set message handler type
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
