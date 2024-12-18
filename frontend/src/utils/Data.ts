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

export interface Transaction {
    
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
}

export interface UserInformation {
    user: User;
    crypto: CryptoInfo[];
    stocks: StockInfo[];
    transactions: Transaction[];
}

export interface BaseInformation {
    loggedIn: boolean;
    loading: boolean;
    userInformation: UserInformation | null;
    news: NewsInfo[];
    token: string;
}

export const server_url:string = "http://localhost:9090";