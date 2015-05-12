import proiectIPModul4.TextAnalyzer;
import com.aylien.textapi.TextAPIClient;
import com.aylien.textapi.TextAPIException;
import com.aylien.textapi.parameters.HashTagsParams;
import com.aylien.textapi.parameters.SummarizeParams;
import com.aylien.textapi.responses.HashTags;

import java.util.ArrayList;

/**
 * Created by Ana on 5/11/2015.
 */
public class HashtagAnalyzer implements TextAnalyzer
{

    TextAPIClient client;
    String text;
    HashTagsParams.Builder builder ;


    public HashtagAnalyzer(TextAPIClient client , String text)
    {
        this.client=client;
        this.text=text;
        builder = HashTagsParams.newBuilder();
    }
    @Override
    public ArrayList<String> analyze() {

        builder.setText(this.text);
        HashTags re = null;
        try {
            re = client.hashtags(builder.build());
        } catch (TextAPIException e) {
            e.printStackTrace();
        }

        ArrayList<String > results = new ArrayList<String >();
        for (String h : re.getHashtags())
            results.add(h);
        return results;

    }
    public void setText(String text)
    {
        this.text=text;
    }
}
