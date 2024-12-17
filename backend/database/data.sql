CREATE DATABASE IF NOT EXISTS node_mysql_crud;
USE node_mysql_crud;

CREATE TABLE IF NOT EXISTS users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    age INT,
    password_hash VARCHAR(100) NOT NULL,
    balance DECIMAL(10, 2) DEFAULT 0
);

CREATE TABLE IF NOT EXISTS cryptos (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    symbol VARCHAR(100) NOT NULL,
    price DECIMAL(10, 2) NOT NULL
);

CREATE TABLE IF NOT EXISTS stocks (
    id INT AUTO_INCREMENT PRIMARY KEY,
    user_id INT NOT NULL,
    crypto_id INT NOT NULL,
    amount DECIMAL(10, 2) NOT NULL,
    FOREIGN KEY (user_id) REFERENCES users(id),
    FOREIGN KEY (crypto_id) REFERENCES cryptos(id)
);

CREATE TABLE IF NOT EXISTS transactions (
    id INT AUTO_INCREMENT PRIMARY KEY,
    user_id INT NOT NULL,
    crypto_id INT NOT NULL,
    amount DECIMAL(10, 2) NOT NULL,
    price DECIMAL(10, 2) NOT NULL,
    type ENUM('buy', 'sell') NOT NULL,
    date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES users(id),
    FOREIGN KEY (crypto_id) REFERENCES cryptos(id)
);


INSERT INTO users (name, email, age, password_hash, balance) 
VALUES ('John Doe', 'john.doe@example.com', 30, sha2('securepassword', 256), 10000.00);

INSERT INTO cryptos (name, symbol, price) 
VALUES 
('Bitcoin', 'BTC', 50000.00),
('Ethereum', 'ETH', 4000.00),
('Cardano', 'ADA', 2.00),
('Polkadot', 'DOT', 40.00),
('Solana', 'SOL', 180.00),
('Binance Coin', 'BNB', 600.00),
('Dogecoin', 'DOGE', 0.25),
('XRP', 'XRP', 1.10),
('Shiba Inu', 'SHIB', 0.000028),
('Avalanche', 'AVAX', 100.00),
('Litecoin', 'LTC', 200.00),
('Chainlink', 'LINK', 30.00),
('Stellar', 'XLM', 0.30),
('VeChain', 'VET', 0.15),
('Uniswap', 'UNI', 25.00),
('Aave', 'AAVE', 300.00),
('Cosmos', 'ATOM', 35.00),
('Algorand', 'ALGO', 2.00),
('Decentraland', 'MANA', 3.50),
('The Sandbox', 'SAND', 5.00),
('Axie Infinity', 'AXS', 150.00),
('FTX Token', 'FTT', 60.00),
('Elrond', 'EGLD', 400.00),
('Theta', 'THETA', 7.00),
('Filecoin', 'FIL', 70.00),
('Tezos', 'XTZ', 5.00),
('Hedera', 'HBAR', 0.35),
('PancakeSwap', 'CAKE', 15.00),
('Near Protocol', 'NEAR', 10.00),
('Harmony', 'ONE', 0.20);

INSERT INTO stocks (user_id, crypto_id, amount)
SELECT 1, id, ROUND(RAND() * 10 + 1, 2) 
FROM cryptos 
LIMIT 30;

INSERT INTO transactions (user_id, crypto_id, amount, price, type)
SELECT 1, id, ROUND(RAND() * 5 + 1, 2), price, 
    CASE WHEN RAND() > 0.5 THEN 'buy' ELSE 'sell' END
FROM cryptos
LIMIT 5;

