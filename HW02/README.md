# 資料結構作業02_解題報告

###### tags: `資料結構` `C`

> 因為事隔半年後才來補這個坑，所以這篇文我不會寫的很詳細，大概提一下我的解法而已，幸好我的扣都有寫註解，如果不懂可以看我的扣。

## 1. Operation Overlord

### 1-1 Set the Allies’ bases optimally

這題題目是以二戰諾曼第登陸為背景，給你一個陣列表示的二元樹狀結構，這顆樹的每一個節點代表一個聯軍的地盤，在地盤上設置碉堡後可以保護到**自己、自己的子節點、自己的父節點**，**請你求出在保護到所有地盤的情況下，所需要的最少碉堡數量**。

像下圖這樣，在B點設置碉堡後，藍色範圍是被保護到的點。

![](https://i.imgur.com/TS0GKd0.png)

這題可以分成兩個部份去解，第一是建立樹，第二是走訪(蓋碉堡)。

#### 建立樹

助教給的測資會是一個字串，像這樣 `[0,0,0,null,null,0,null,null,0]`，0表示地盤，null表示沒有節點，上面測資畫成樹後長這樣：

![](https://i.imgur.com/v7Mm8m8.png)

我用到Queue來保存加入樹中的節點，下次從Queue拿出來時，便成為新節點的父節點，如果是null則直接跳過，不必加入Queue中。

#### 走訪(蓋碉堡)

接下來是利用 **後序走訪** 來決定是否要蓋碉堡，走訪節點後會回傳一個數字，表示是否要蓋碉堡的情況。

* **接收到-1**，表示該點被他的子節點保護到了，向父節點傳0。
* **接收到0**，表示該點的子節點並沒有保護到他，需要向父節點傳1。
* **接收到1**，表示該點底下的子節點沒有人保護，所以一定要蓋碉堡，並向父節點傳-1
* 如果是null，則回傳0
* 如果是root接收到0，因為root上面已經沒有父節點可以保護他了，所以在要root蓋碉堡。

這樣走訪完所有的點後，碉堡樹就是答案了。

### 1-2 Set the Allies’ bases optimally - II 

這題與1-1不同點在於，每個地盤上多了蓋碉堡所需要花費的成本，**請你求出在保護所有地盤的情況下，所需花費的最小成本**。

建立樹的部分和1-1一樣，只是這題多加了成本而已。

走訪的部分不能再用第一題的貪婪演算法，不能單純回傳一個值，而是必須回傳三個值才能決定，但時間隔太久了，我也忘記當初是怎麼想的QQ，就看我的code自己通靈一下吧OAO。

### 1-3 Spot the liars

在戰爭中，我方抓到了N位戰俘，其中有M位是騙子，N-M位是好人，騙子永遠都會說謊，而好人永遠都講實話，測資長這樣：

```
3 (N)    // 3位戰俘
1 (M)    // 1位騙子
0>1=T    // 0說1是好人
1>2=L    // 1說2是騙子
2>0=L    // 2說0是騙子

Output: 2
```

綜合以上三句描述，我們可以推論出騙子是2，可以假設答案是唯一的。

我們觀察到一句話裡面，如果經過1個騙子，那麼這句話會變成錯的，但再經過1個騙子，這句話又變成對的，也就是說 **一句話中如果有奇數個騙子，那這句話是錯的，如果有偶數個騙子，那這句話是對的**。

我們就用一個**N\*N的矩陣來統計每一句話人物出現的次數**，接著因為我們知道有M個騙子，所以就**列舉所有M個騙子的組**合，一一代入話中驗證是否正確，如果全部的話都正確，這個就是答案。

列舉的部分當初太菜了，沒有寫得很好，其實用遞迴列舉更好。

## 2. Trolley Problem

雖然和列車難題沒什麼關係就是了XD。

### 2-1 Build a doubly and circular linked list

請實作一個20個節點的**雙向環狀串列**，一個節點代表一個月台(下一題會用到)。

很簡單就是在送分，課本上都有，我就不解釋了(絕不是我懶)。

### 2-2 Try to optimize the process

在這之前我們要先看懂幾個符號：

* `>`：向右移一個月台
* `<`：向左移一個月台
* `+`：月台的字母+1，Y->Z->(space)->A->B
* `-`：月台的字母-1，B->A->(space)->Z->Y
* `.`：發車

總之要透過這幾個符號來操控月台發車順序。

問題是反過來，給你一串發車順序，請你求出完成任務所需最少的指令。

順帶一提，這題是依照你的指令長度部份給分，要在助教的標準解答的-5%內，才能得到滿分。

#### 貪婪法

就每次找 **移動步數成本+切換字母成本** 最小的，步數用正負號決定向左或向右，切換字母也是，比較大小時再轉絕對值。

雖然這方法不是最佳解，但已經助教的標準解答-5%內了，我就沒有繼續想要如何優化了。

## 小結

第一題用到二元樹以及後序走訪的概念，第二題則用了環狀串鍊的概念，都是不錯的應用，試著自己寫寫看會滿有收穫的。

哎呀，實在是拖得太久了，這一拖就是半年了，現在回頭看自己寫的code，發現很多地方都寫得不乾淨，所以也不要全照著我的寫法，自己想想看有沒有更佳的解法。

> 看完覺得有幫助的話，就幫我點個右上角的star吧! 你的鼓勵是我繼續創作的原動力~

by @AndyChiang 

> [time=Wed, Jul 14, 2021 4:12 PM]