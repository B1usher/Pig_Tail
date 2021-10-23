// pages/denglu/denglu.js
var app=getApp();
Page({

  /**
   * 页面的初始数据
   */
  data: {
    yhm:'',
    mm:''
  }, 
  getyhm(res){
    this.setData({yhm:res.detail.value})
  },
  getmm(res){
    this.setData({mm:res.detail.value})
  },
 
  denglu()
  {
    wx.request({
      url: 'http://172.17.173.97:8080/api/user/login',
      method:'post',
      data:{student_id:this.data.yhm,password:this.data.mm},
      header:{'content-type':'application/x-www-form-urlencoded'},
      success(res){
        console.log(res.data);
        console.log(res.data.data.token);
        console.log(typeof(res.data.data.token) );
        if(res.data.status==200)
        {
          wx.showToast({
            title: '登录成功',
          })
          wx.setStorageSync('key', res.data.data.token);
          wx.navigateTo({
            url: '/pages/online/online',
          })
        }
        else{
          wx.showToast({
            title: "网络出错",
            icon:'error',
            duration:1000
          })
        }
      },
      fail(res){
        wx.showToast({
          title: 'gulugulu',
          icon:'error',
          duration:1000
        })
      }
    })
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