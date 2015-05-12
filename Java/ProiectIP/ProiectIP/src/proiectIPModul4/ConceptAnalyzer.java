import proiectIPModul4.TextAnalyzer;
import com.aylien.textapi.TextAPIClient;
import com.aylien.textapi.TextAPIException;
import com.aylien.textapi.parameters.ConceptsParams;
import com.aylien.textapi.responses.Concept;
import com.aylien.textapi.responses.Concepts;
import com.aylien.textapi.responses.SurfaceForm;

import java.lang.reflect.Array;
import java.util.ArrayList;

/**
 * Created by Ana on 5/11/2015.
 */
public class ConceptAnalyzer implements TextAnalyzer
{
    TextAPIClient client;
    String text;
    ConceptsParams.Builder builder ;
    public ConceptAnalyzer(TextAPIClient client , String text)
    {
        this.client=client;
        this.text=text;
        builder = ConceptsParams.newBuilder();
    }

    public ArrayList<String> analyze()
    {
        builder.setText(this.text);
        Concepts concepts = null;
        try {
            concepts = client.concepts(builder.build());
        } catch (TextAPIException e) {
            e.printStackTrace();
        }
        ArrayList<String > results = new ArrayList<String >();
        for (Concept c: concepts.getConcepts()) {
            for (SurfaceForm sf: c.getSurfaceForms()) {
               // System.out.println(sf.getString());
                results.add(sf.getString());
            }
        }
        return results;
    }
}
