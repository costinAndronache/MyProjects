import proiectIPModul4.TextAnalyzer;
import com.aylien.textapi.TextAPIClient;
import com.aylien.textapi.TextAPIException;
import com.aylien.textapi.parameters.HashTagsParams;
import com.aylien.textapi.parameters.SentimentParams;
import com.aylien.textapi.responses.HashTags;
import com.aylien.textapi.responses.Sentiment;

import java.util.ArrayList;

/**
 * Created by Ana on 5/11/2015.
 */
public class PerspectiveAnalyzer implements TextAnalyzer
{
    TextAPIClient client;
    String text;
    SentimentParams.Builder builder ;


    public PerspectiveAnalyzer(TextAPIClient client , String text)
    {
        this.client=client;
        this.text=text;
        builder = SentimentParams.newBuilder();
    }
    @Override
    public ArrayList<String> analyze() {

        builder.setText(this.text);
        Sentiment re = null;
        try {
            re = client.sentiment(builder.build());
        } catch (TextAPIException e) {
            e.printStackTrace();
        }

        ArrayList<String > results = new ArrayList<String >();
        results.add(re.getSubjectivity());
        return results;

    }
    public void setText(String text)
    {
        this.text=text;
    }
}
