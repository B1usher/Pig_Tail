// pages/bendi/bendi.js
Page({

  /**
   * 页面的初始数据
   */
  data: {
    paidui:0,
    shengyu:52,
    p1fang:0,
    p1mei:0,
    p1hong:0,
    p1hei:0,
    p2fang:0,
    p2mei:0,
    p2hong:0,
    p2hei:0,
    syfang:13,
    symei:13,
    syhong:13,
    syhei:13,
    ljfang:0,
    ljmei:0,
    ljhong:0,
    ljhei:0,
    key:10,
    flag:0,
    f0:1,
    f1:1,
    f2:1,
    f3:1,
    ai:1
  },
  ai()
  {
    var amount=[this.data.syfang,this.data.symei,this.data.syhong,this.data.syhei]; 
    var shoupai=[this.data.p1fang,this.data.p1mei,this.data.p1hong,this.data.p1hei];
    var amount1=[this.data.p2fang,this.data.p2mei,this.data.p2hong,this.data.p2hei];
    var score=[0,0,0,0,0];
    score[0] = 3;
    if(this.data.shengyu<=10)
    {
      if(this.data.syfang==0)score[0] +=13;
      if(this.data.symei==0)score[0] +=13;
      if(this.data.syhong==0)score[0] +=13; 
      if(this.data.syhei==0)score[0] +=13;
    }
    for (var i = 0; i < 4; i++)
    {
      if (shoupai[i] != 0)	
      {
        for (var j = 0; j < 4; j++)
        {
          if (amount[j] <= amount[i])
          score[i + 1] += 1;
          if (amount1[j] <= amount1[i])
          score[i + 1] += 1;
        }
        score[i + 1] += 4;
      }
      else score[1+i]=0;
    }   
    if(this.data.paidui)
    score[1+this.data.key]=0;
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
    this.qupai();
    else if(tag==4)
    this.chuhei1();
    else if(tag==3)
    this.chuhong1();
    else if(tag==2)
    this.chumei1();
    else if(tag==1)
    this.chufang1();
    console.log(tag);
  },
  xiaojie()
    {
      if(this.data.flag%2)
          {
            var fang=this.data.p1fang+this.data.ljfang;
            var mei=this.data.p1mei+this.data.ljmei;
            var hong=this.data.p1hong+this.data.ljhong;
            var hei=this.data.p1hei+this.data.ljhei;
            this.setData({
            p1fang:fang,
            p1mei:mei,
            p1hong:hong,
            p1hei:hei,
            ljfang:0,
            ljmei:0,
            ljhong:0,
            ljhei:0,     
            paidui:0,
            key:10
          })
          }
          else
          {
            var fang=this.data.p2fang+this.data.ljfang;
            var mei=this.data.p2mei+this.data.ljmei;
            var hong=this.data.p2hong+this.data.ljhong;
            var hei=this.data.p2hei+this.data.ljhei;
            this.setData({
            p2fang:fang,
            p2mei:mei,
            p2hong:hong,
            p2hei:hei,
            ljfang:0,
            ljmei:0,
            ljhong:0,
            ljhei:0,     
            paidui:0,
            key:10
          })
          }
  },

  qupai()
  {
    var num1=this.data.shengyu;
    var num2=this.data.paidui;
    num1--,
    num2++;
    this.setData({
      shengyu:num1,
      paidui:num2
    })
    var temp=Math.round(Math.random()*3);
    while(1)
    { 
      temp=Math.round(Math.random()*3);
      if(temp==0&&this.data.f0!=0||temp==1&&this.data.f1!=0||temp==2&&this.data.f2!=0||temp==3&&this.data.f3!=0)break;    
    }
    if(temp==0)
    {
      var s=this.data.syfang;
      var l=this.data.ljfang;
      s--;
      l++;
      this.setData({
      syfang:s,
      ljfang:l
      })
      if(this.data.key==temp){this.xiaojie();}
      else if(this.data.paidui!=0){this.setData({key:0})}
      
    }
    else if(temp==1)
    {
      var s=this.data.symei;
      var l=this.data.ljmei;
      s--;
      l++;
      this.setData({
      symei:s,
      ljmei:l
      })

      if(this.data.key==temp){this.xiaojie();}
      else if(this.data.paidui!=0){this.setData({key:1})}
       
    }
    else if(temp==2)
    {
      var s=this.data.syhong;
      var l=this.data.ljhong;
      s--;
      l++;
      this.setData({
      syhong:s,
      ljhong:l
      })

      if(this.data.key==temp){this.xiaojie();}
      else if(this.data.paidui!=0){this.setData({key:2})}
      
    }
    else if(temp==3)
    {
      var s=this.data.syhei;
      var l=this.data.ljhei;
      s--;  
      l++; 
      this.setData({
      syhei:s,
      ljhei:l
      })

      if(this.data.key==temp){this.xiaojie();}
      else if(this.data.paidui!=0){this.setData({key:3})}
      
    }
    if(this.data.syfang==0)this.setData({f0:0})
    if(this.data.symei==0)this.setData({f1:0})
    if(this.data.syhong==0)this.setData({f2:0})
    if(this.data.syhei==0)this.setData({f3:0})

    if(this.data.shengyu==0) 
    {
      var p1=this.data.p1fang+this.data.p1mei+this.data.p1hong+this.data.p1hei;
      var p2=this.data.p2fang+this.data.p2mei+this.data.p2hong+this.data.p2hei;
      if(p1<p2) 
      {
        wx.showToast({
        title: 'p1 win',
        icon:"none",
        duration:2000
        });
      }
      else if(p1>p2)
      {
        wx.showToast({
          title: 'p2 win',
          icon:"none",
          duration:2000
          });
      }
      else{
        wx.showToast({
          title: '真菜，还会平局',
          icon:"none",
          duration:2000
          });
      }
      
    }
    this.xiayiwei();
    console.log(this.data.key);
    console.log(this.data.flag);
    if(this.data.flag%2)
    this.ai();
    // if(this.data.flag%2)
    // this.ai(this.data.p1fang,this.data.p1mei,this.data.p1hong,this.data.p1hei,this.data.p2fang,this.data.p2mei,this.data.p2hong,this.data.p2hei,this.data.syfang,this.data.symei,this.data.syhong,this.data.syhei,this.data.paidui,this.data.key);
    
  }, 

  chufang2(){
    var temp=this.data.p2fang;
    temp--;
    var lj=this.data.ljfang;
    lj++;
    var pd=this.data.paidui;
    pd++;
    this.setData({p2fang:temp,paidui:pd,ljfang:lj})
    if(this.data.key==0)this.xiaojie();
    else this.setData({key:0})
    this.xiayiwei();
  },
  chumei2(){
    var temp=this.data.p2mei;
    temp--;
    var lj=this.data.ljmei;
    lj++;
    var pd=this.data.paidui;
    pd++;
    this.setData({p2mei:temp,paidui:pd,ljmei:lj})
    if(this.data.key==1)this.xiaojie();
    else this.setData({key:1});
    this.xiayiwei();
  },
  chuhong2(){
    var temp=this.data.p2hong;
    temp--;
    var lj=this.data.ljhong;
    lj++;
    var pd=this.data.paidui;
    pd++;
    this.setData({p2hong:temp,paidui:pd,ljhong:lj})
    if(this.data.key==2)this.xiaojie();
    else this.setData({key:2});
    this.xiayiwei();
  },
  chuhei2(){
    var temp=this.data.p2hei;
    temp--;
    var lj=this.data.ljhei;
    lj++;
    var pd=this.data.paidui;
    pd++;
    this.setData({p2hei:temp,paidui:pd,ljhei:lj})
    if(this.data.key==3)this.xiaojie();
    else this.setData({key:3});
    this.xiayiwei();
  },
  chufang1(){
    var temp=this.data.p1fang;
    temp--;
    var lj=this.data.ljfang;
    lj++;
    var pd=this.data.paidui;
    pd++;
    this.setData({p1fang:temp,paidui:pd,ljfang:lj})
    if(this.data.key==0)this.xiaojie();
    else this.setData({key:0});
    this.xiayiwei();
  },
  chumei1(){
    var temp=this.data.p1mei;
    temp--;
    var lj=this.data.ljmei;
    lj++;
    var pd=this.data.paidui;
    pd++;
    this.setData({p1mei:temp,paidui:pd,ljmei:lj})
    if(this.data.key==1)this.xiaojie();
    else this.setData({key:1});
    this.xiayiwei();
  },
  chuhong1(){
    var temp=this.data.p1hong;
    temp--;
    var lj=this.data.ljhong;
    lj++;
    var pd=this.data.paidui;
    pd++;
    this.setData({p1hong:temp,paidui:pd,ljhong:lj})
    if(this.data.key==2)this.xiaojie();
    else this.setData({key:2});
    this.xiayiwei();
  }, 
  chuhei1(){
    var temp=this.data.p1hei;
    temp--;
    var lj=this.data.ljhei;
    lj++;
    var pd=this.data.paidui;
    pd++;
    this.setData({p1hei:temp,paidui:pd,ljhei:lj})
    if(this.data.key==3)this.xiaojie();
    else this.setData({key:3})
    this.xiayiwei();

  },

  xiayiwei(){
    var f=this.data.flag;
    f++;
    this.setData({flag:f});
  },
  


 
  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {

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