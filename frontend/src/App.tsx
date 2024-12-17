import React, { createContext, useState, useEffect } from 'react';
import { BrowserRouter as Router, Routes, Route, Link } from 'react-router-dom';
import Home from './pages/Home';
import About from './pages/About';
import NoMatch from './pages/NoMatch';
import Crypto from './pages/Crypto';
import News from './pages/News';
import Stocks from './pages/Stocks';
import Bank from './pages/Bank';
import { BaseInformation } from './utils/Data';
import Login from './pages/Login';
/*
APIs to Integrate:

    Stock Market API (e.g., Alpha Vantage or Yahoo Finance):
        Fetch live stock data and charts.
    Cryptocurrency API (e.g., CoinGecko or Binance):
        Display cryptocurrency prices and market trends.
    News API (e.g., NewsAPI):
        Show market-related news articles.
*/


export const BaseInformationContext = createContext<{
  baseInformation: BaseInformation | null;
  setBaseInformation: React.Dispatch<React.SetStateAction<BaseInformation | null>>;
} | null>(null);

function App() {
  const [baseInformation, setBaseInformation] = useState<BaseInformation | null>(null);

  useEffect(() => {
    const savedBaseInfo = localStorage.getItem('baseInformation');
    if (savedBaseInfo) {
      setBaseInformation(JSON.parse(savedBaseInfo));
    }


  }, []);

  useEffect(() => {
    if (baseInformation) {
      localStorage.setItem('baseInformation', JSON.stringify(baseInformation));
    }
  }, [baseInformation]);

  
  return (
    <BaseInformationContext.Provider value={{ baseInformation, setBaseInformation }}>
      <Router>
        <div className="App">
          <nav>
            <ul>
              <li><Link to="/">Home</Link></li>
              <li><Link to="/about">About</Link></li>
            </ul>
          </nav>

          <Routes>
            <Route path="/login" element={<Login />} />
            <Route path="/" element={<Home />} />
            <Route path="/about" element={<About />} />
            <Route path="*" element={<NoMatch />} />
            <Route path="/crypto" element={<Crypto />} />
            <Route path="/news" element={<News />} />
            <Route path="/stocks" element={<Stocks />} />
            <Route path="/bank" element={<Bank />} />
          </Routes>
        </div>
      </Router>
    </BaseInformationContext.Provider>
  );
}

export default App;
