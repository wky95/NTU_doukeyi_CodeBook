vector<point> convex_hull(vector<point> v){
 
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end())-v.begin());
    vector<point> hull;
 
    for (int _=0 ; _<2 ; _++){
        int sz=hull.size();
 
        for (int i=0 ; i<v.size() ; i++){
            while (hull.size()>=sz+2 && ori(hull[hull.size()-2], hull[hull.size()-1], v[i])<0){
                hull.pop_back();
            }
            hull.push_back(v[i]);
        }
 
        hull.pop_back();
        reverse(v.begin(), v.end());
    }
 
    return hull;
}