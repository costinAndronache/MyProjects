import proiectIPModul4.TextAnalyzer;
import com.aylien.textapi.TextAPIClient;
import com.aylien.textapi.TextAPIException;
import com.aylien.textapi.parameters.ConceptsParams;
import com.aylien.textapi.parameters.SummarizeParams;
import com.aylien.textapi.responses.Concept;
import com.aylien.textapi.responses.Concepts;
import com.aylien.textapi.responses.Summarize;
import com.aylien.textapi.responses.SurfaceForm;

import java.util.ArrayList;

/**
 * Created by Ana on 5/11/2015.
 */
public class SummaryAnalyzer implements TextAnalyzer
{
    TextAPIClient client;
    String text;
    SummarizeParams.Builder builder ;
    String title;

    public SummaryAnalyzer(TextAPIClient client , String text , String title)
    {
        this.client=client;
        this.text=text;
        this.title=title;
        builder = SummarizeParams.newBuilder();
    }
    @Override
    public ArrayList<String> analyze()
    {
        builder.setText(this.text);
        builder.setTitle(this.title);

        Summarize summ = null;
        try {
            summ = client.summarize(builder.build());
        } catch (TextAPIException e) {
            e.printStackTrace();
        }

        ArrayList<String > results = new ArrayList<String >();
        for ( String sent : summ.getSentences())
        {
           results.add(sent);
        }

        return results;
    }
    public void setText(String text)
    {
        this.text=text;
    }
    public void setTitle(String text)
    {
        this.title=text;
    }
}
