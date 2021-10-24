// pages/online/online.js
var app=getApp();
Page({

  /**
   * 页面的初始数据
   */
  data: {
    uuid:'',
    uuid1:'',
    urltemp:'http://172.17.173.97:9000/api',
    index:'',
    size:'5',
    arr:[],
    arr1:[]
  },
  cj(){
      wx.request({
        url: 'http://172.17.173.97:9000/api/game',
        method:'post',
        data:{private:false},
        header:{'Authorization':wx.getStorageSync('key')},
        success(res)
        {
          console.log('Bearer'+wx.getStorageSync('key'));
          console.log(res.data);
          wx.showToast({title: '创建成功',})
          wx.setStorageSync('uuid', res.data.data.uuid);
          wx.navigateTo({
            url: '/pages/play/play',
          })
        },
        fail(res)
        {wx.showToast({title: '创建失败',})}
      })

  },
  
  getuuid(res){
    this.setData({uuid:res.detail.value});
  },
  jr(){
    console.log(this.data.uuid);
    wx.setStorageSync('uuid', this.data.uuid);
    wx.request({
      url: 'http://172.17.173.97:9000/api/game/'+this.data.uuid,
      method:'post',
      header:{Authorization:wx.getStorageSync('key')},
      success(res)
      {
        wx.showToast({title: '加入成功',})
       
        wx.navigateTo({
          url: '/pages/play/play',
        }) 
      },
      fail(res)
      {wx.showToast({title: '加入失败',})}
    })
  },
  getuuid1(res){
    this.setData({uuid1:res.detail.value});
  },
  cx(){
    wx.request({
      url: 'http://172.17.173.97:9000/api/game/'+this.data.uuid1,
      method:'get',
      header:{Authorization:wx.getStorageSync('key'),
      'content-type':'application/x-www-form-urlencoded'},
      success(res){
        wx.showToast({title: '查询成功',})
        wx.setStorageSync('data1', res.data);
        wx.navigateTo({
          url: '/pages/logs/logs',
        });
        console.log(res.data.data);
      },
      fail(res)
      {wx.showToast({title: '查询失败',})}
    })

  },
  getindex(res){
    this.setData({index:res.detail.value})
  },
  hq()
  {
    console.log(this.data.size);
    console.log(this.data.index);
    wx.request({
          url: 'http://172.17.173.97:9000/api/game/index',
          method:'get',
          header:{Authorization:wx.getStorageSync('key'),'content-type':'application/x-www-form-urlencoded'},
          data:{page_size:this.data.size,page_num:this.data.index},
          success(res)
          {
            console.log(res.data.data.games) ;
            wx.showToast({title: '获取成功',})
            wx.setStorageSync('data', res.data.data.games);
          },
          fail(res)
          {wx.showToast({title: '获取失败',})}
        })
        var temp=wx.getStorageSync('data');
        
        this.setData({arr:temp});
        console.log(this.data.arr);
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