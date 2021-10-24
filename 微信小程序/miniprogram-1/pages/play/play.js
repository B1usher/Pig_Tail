// pages/bendi/bendi.js
Page({

  /**
   * 页面的初始数据
   */
  data: {
    uuid:'',
    paidui:0,
    shengyu:52,
    key:'UN',
    flag:undefined,
    pfang:0,
    pmei:0,
    phong:0,
    phei:0,
    paiduifang:[],
    paiduimei:[],
    paiduihong:[],
    paiduihei:[],
    shoufang:[],
    shoumei:[],
    shouhong:[],
    shouhei:[],
    op:0,
    card:'',
    k:1,
    fang:0,
    mei:0,
    hong:0,
    hei:0
  },
  ai()
  {

    this.get();
    var shoupai=[this.data.shoufang.length,this.data.shoumei.length,this.data.shouhong.length,this.data.shouhei.length];
    var amount1=[this.data.pfang,this.data.pmei,this.data.phong,this.data.phei];
    var score=[0,0,0,0,0];
    score[0] = 3;
    for (var i = 0; i < 4; i++)
    {
      if (shoupai[i] != 0)	
      {
        for (var j = 0; j < 4; j++)
        {
          if (amount1[j] <= amount1[i])
          score[i + 1] += 1;
        }
        score[i + 1] += 4;
      }
      else score[1+i]=0;
    }   
    if(this.data.key=='UN');
    else if(this.data.key=='D')
    score[1]=0;
    else if(this.data.key=='C')
    score[2]=0;
    else if(this.data.key=='H')
    score[3]=0;
    else if(this.data.key=='S')
    score[4]=0;
    
    var max=0,tag=0;
    for(var i=0;i<5;i++)
    {
      if(score[i]>=max){
        tag=i;
        max=score[i];
      }
    }
    console.log(score);
    if(tag==0)
    this.fanpai();
    else if(tag==4)
    this.chuhei();
    else if(tag==3)
    this.chuhong();
    else if(tag==2)
    this.chumei();
    else if(tag==1)
    this.chufang();
    console.log(tag);
  },



  fanpai(){
    this.setData({op:0});
    this.put();
  },
  chufang(){
    var temp=shoufang;
    this.setData({op:1,card:temp[temp.length-1]});
    this.put();
  },
  chumei(){
    var temp=shoumei;
    this.setData({op:1,card:temp[temp.length-1]});
    this.put();
  },
  chuhong(){
    var temp=shouhong;
    this.setData({op:1,card:temp[temp.length-1]});
    this.put();
  },
  chuhei(){
    var temp=shouhei;
    this.setData({op:1,card:temp[temp.length-1]});
    this.put();
  },

  put(){
    wx.request({
      url: 'http://172.17.173.97:9000/api/game/'+this.data.uuid,
      method:'put',
      data:{type:this.data.op,card:this.data.card},
      header:{'Authorization':wx.getStorageSync('key')},
      success(res){
        wx.setStorageSync('data', res.data);
      },
      fail(res)
      {
        wx.showToast({title: '获取失败',});
      }
    })
    var temp=wx.getStorageSync('data');
    console.log(temp);
    if(temp.code!=200)
    {
      wx.showToast({title: '人没到齐或结束',});
    }
    else{
      this.chupai();
      this.setData({k:1});
    }
  },


  chupai(){
    var temp=wx.getStorageSync('data');
    var opearate=temp.data.last_code.substring(2,3);
    var kind=temp.data.last_code.substring(4,5);
    var card=temp.data.last_code.substring(4);
    var sy=this.data.shengyu;
    if(opearate=='0')
    {
      sy--;
      this.setData({shengyu:sy});
      this.jiarupaidui(kind,card);
    }
    else{
        if(kind=='D')
        {
          var pfa=this.data.shoufang;
          var td=this.data.paiduifang;
          td.push(pfa.pop);
          this.setData({shoufang:pfa,paiduifang:td});
        }
        if(kind=='C')
        {
          var pme=this.data.shoumei;
          var td=this.data.paiduimei;
          td.push(pme.pop);
          this.setData({shoumei:pme,paiduimei:td});
        }
        if(kind=='H')
        {
          var pho=this.data.shouhong;
          var td=this.data.paiduihong;
          td.push(pho.pop);
          this.setData({shouhong:pho,paiduihong:td});
        }
        if(kind=='S')
        {
          var phe=this.data.shouhei;
          var td=this.data.paiduihei;
          td.push(phe.pop);
          this.setData({shouhei:phe,paiduihei:td});
        }  
    }
    if(kind==this.data.key)
    {
      this.qingchu();
      this.setData({key:'UN'});
    }
    
    else{
      this.setData({key:kind});
    }

    this.setDate({fang:shoufang.length,mei:shoumei.length,hong:shouhong.length,hei:shouhei.length,});
  },

  qingchu(){
    var fang=this.data.shoufang.concat(this.data.paiduifang);
    var mei=this.data.shoumei.concat(this.data.paiduimei);
    var hong=this.data.shouhong.concat(this.data.paiduihong);
    var hei=this.data.shouhei.concat(this.data.paiduihei);
    var arr=[];
    this.setData({shoupaifang:fang,shoupaimei:mei,shoupaihong:hong,shoupaihei:hei,paiduifang:arr,paiduimei:arr,paiduihong:arr,paiduihei:arr});

  },

  get()
  {
    wx.request({
        url: 'http://172.17.173.97:9000/api/game/'+this.data.uuid+'/last',
        method:'get',
        header:{Authorization:wx.getStorageSync('key')},
        success(res)
        {
         
          wx.setStorageSync('data', res.data);
          console.log(res.data.msg);
        },
        fail(res)
        {
          wx.showToast({title: '获取失败',});
        }
      })
      var temp=wx.getStorageSync('data');
      var a;
      var b;
      // if(this.data.k)
      // {
      //   clearTimeout(a);
      //   clearTimeout(b);
      // }
      // else 
      if(temp.code==403)
      {
        // a=setTimeout(()=>{
        //     this.get();
        //   }
        // ,5000)
        wx.showToast({
          title: '403',
        })
      } 
      else if(temp.data.your_turn==false)
      {
        this.setData({flag:1});
        // b=setTimeout(()=>{
        //   this.get();
        //   },1000)
        wx.showToast({title: '不是你的回合',});
      }
      else{
        wx.showToast({title: '当前轮到您出牌',});
        if(temp.data.last_msg=="对局刚开始")   ;
        else{
          if(this.data.k)
          this.jiexi();
        }
        this.setData({flag:0});
      }
  },

  jiexi()
  {
    var temp=wx.getStorageSync('data');
    var opearate=temp.data.last_code.substring(2,3);
    var kind=temp.data.last_code.substring(4,5);
    var card=temp.data.last_code.substring(4);
    var sy=this.data.shengyu;
    if(opearate=='0')
    {
      sy--;
      this.setData({shengyu:sy});
    }
    else{
        if(kind=='D')
        {
          var pfa=this.data.pfang;
          pfa--;
          this.setData({pfang:pfa});
        }
        if(kind=='C')
        {
          var pme=this.data.pmei;
          pme--;
          this.setData({pmei:pme});
        }
        if(kind=='H')
        {
          var pho=this.data.phong;
          pho--;
          this.setData({phong:pho});
        }
        if(kind=='S')
        {
          var phe=this.data.phei;
          phe--;
          this.setData({phei:phe});
        }  
    }
    this.jiarupaidui(kind,card);
    if(kind==this.data.key)
    {
      this.xiaojie();
      this.setData({key:'UN'});
    }
    else
    this.setData({key:kind});
    this.setDate({fang:shoufang.length,mei:shoumei.length,hong:shouhong.length,hei:shouhei.length,});
    this.setData({k:0});
  },

  jiarupaidui(a,b)
  {
    if(a=='D'){
      var temp=this.data.paiduifang;
      temp.push(b);
      this.setData({paiduifang:temp});
    } 
    if(a=='C'){
      var temp=this.data.paiduimei;
      temp.push(b);
      this.setData({paiduimei:temp});
    } 
    if(a=='H'){
      var temp=this.data.paiduihong;
      temp.push(b);
      this.setData({paiduihong:temp});
    }
    if(a=='S'){
      var temp=this.data.paiduihei;
      temp.push(b);
      this.setData({paiduihei:temp});
    } 
  },
  xiaojie(){
    var pfa=this.data.pfang;
    var pme=this.data.pmei;
    var pho=this.data.phong;
    var phe=this.data.phei;
    pfa=pfa+this.data.paiduifang.length;
    pme=pme+this.data.paiduimei.length; 
    pho=pho+this.data.paiduihong.length;
    phe=phe+this.data.paiduihong.length;
    var arr=[];
    this.setData({paiduifang:arr,paiduimei:arr,paiduihong:arr,paiduihei:arr,pfang:pfa,pmei:pme,phong:pho,phei:phe});
  },







 
  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    this.setData({uuid:wx.getStorageSync('uuid')});
    this.get();
  },

  /**
   * 生命周期函数--监听页面初次渲染完成
   */
  onReady: function () {

  },

  /**
   * 生命周期函数--监听页面显示
   */
  onShow: function () {

  },

  /**
   * 生命周期函数--监听页面隐藏
   */
  onHide: function () {

  },

  /**
   * 生命周期函数--监听页面卸载
   */
  onUnload: function () {

  },

  /**
   * 页面相关事件处理函数--监听用户下拉动作
   */
  onPullDownRefresh: function () {

  },

  /**
   * 页面上拉触底事件的处理函数
   */
  onReachBottom: function () {

  },

  /**
   * 用户点击右上角分享
   */
  onShareAppMessage: function () {

  }
})