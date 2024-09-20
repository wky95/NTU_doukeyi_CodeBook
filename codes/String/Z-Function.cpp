vector<int> z_value;
void z_function(string s){
    z_value.resize(s.size());
    int ll = 0, rr = 0;

    for (int i=1 ; i<s.size() ; i++){
        int j = 0;

        if (i<rr) j = min(z_value[i-ll], rr-i);
        while (s[j]==s[i+j]) j++;
        z_value[i] = j;

        if (i+j>rr){
            ll = i;
            rr = i+j;
        }
    }

    z_value[0] = s.size();
    return;
}