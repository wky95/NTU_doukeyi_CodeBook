vector<point> convex_hull(vector<point> points){
 
    sort(points.begin(), points.end());
    vector<point> hull;
 
    for (int _=0 ; _<2 ; _++){
        int sz=hull.size();
 
        for (int i=0 ; i<points.size() ; i++){
            while (hull.size()>=sz+2 && ori(hull[hull.size()-2], hull[hull.size()-1], points[i])<0){
                hull.pop_back();
            }
            hull.push_back(points[i]);
        }
 
        hull.pop_back();
        reverse(points.begin(), points.end());
    }
 
    return hull;
}