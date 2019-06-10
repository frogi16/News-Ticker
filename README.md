# News Ticker
The News Ticker project aims to be an useful tool to catch up with recent events and news. It downloads news from few chosen sites and displays it on the news ticker similar to these known from TV.

![animated ticker preview](https://user-images.githubusercontent.com/44038381/59218058-9d903980-8bbf-11e9-9dfe-e890546c465d.gif)

At the moment it cannot be considered even partly-completed. Main functionality of scraping is based on my previous projects and the rest is basically a prototype. Splitting the code int more functions and classes has to be done ASAP.

News displayed on the ticker are obtained in process of scraping websites instead of e.q. parsing RSS.

Due to difficulties with constant and continuous displaying ticker on top of every window right now code is not portable. Unfortunately a few lines of code rely on WinAPI. Further research may allow to port this program to other systems.

![full screen preview](https://user-images.githubusercontent.com/44038381/46820664-0d2afc00-cd87-11e8-9022-f4e25b84c3e6.PNG)
