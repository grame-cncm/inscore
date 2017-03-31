

interface Address					{ ip: string, port: number, osc: string; }; 
interface Message					{ address: Address, params: Array<any> }; 
