//map
import 'package:flutter_baidu_mapapi_base/flutter_baidu_mapapi_base.dart';
//location
import 'package:flutter_bmflocation/bdmap_location_flutter_plugin.dart';


class BaiduRegister {

  static String BaiduAK = 'Rq65M1UcTHTzav4RjgFq2870';
  static BMF_COORD_TYPE BaiduCoordType = BMF_COORD_TYPE.BD09LL;

  static void RegisterAK() {
    LocationFlutterPlugin.setApiKey(BaiduAK);
    BMFMapSDK.setApiKeyAndCoordType(BaiduAK, BaiduCoordType);
    BMFMapSDK.setCoordType(BaiduCoordType);
  }

}