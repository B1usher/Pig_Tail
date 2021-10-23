Page({
  data:{
    arr:[]
  },
  onLoad: function (options) {
    var temp=wx.getStorageSync('data1');
    this.setData({arr:temp});
  },
})