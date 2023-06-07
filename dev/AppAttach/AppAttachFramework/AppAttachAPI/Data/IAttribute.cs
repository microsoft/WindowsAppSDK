namespace AppAttachAPI.Data
{
    public interface IAttribute
    {
        string getAttributeName();
        string getAttributeValue();
        void setAttributeValue(string value);
        bool getAttributeValidationStatus();
    }
}
