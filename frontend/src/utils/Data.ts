export interface CryptoInfo {
    name: string;
    id: number;
    symbol: string;
    price: number;
}

export interface NewsInfo {
    title: string;
    id: number;
    description: string;
    url: string;
}

export interface StockInfo {
    name: string;
    id: number;
    symbol: string;
    price: number;
}

export interface User {
    id: number;
    name: string;
    email: string;
    password: string;
    balance: number;
    crypto: CryptoInfo[];
    stocks: StockInfo[];
}

export interface BaseInformation {
    loggedIn: boolean;
    user: User | null;
    news: NewsInfo[];
}

export const server_url:string = "http://localhost:9090";