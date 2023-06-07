using AppAttachAPI.Data;
using System;

namespace AppAttachAPI.Utils
{
    /// <summary>
    /// Provides utility methods for working with assembly types and attributes.
    /// </summary>
    public static class AssemblyUtils
    {
        private const string NAMESPACE = "AppAttachAPI.AttributeImpls.";

        /// <summary>
        /// Returns an instance of the class that implements the specified attribute.
        /// </summary>
        /// <param name="fullyQualifiedName">The fully qualified name of the attribute class.</param>
        /// <returns>An instance of the class that implements the specified attribute, or null if the attribute class is not found.</returns>
        public static IAttribute GetAttributeInstance(string fullyQualifiedName)
        {
            fullyQualifiedName = NAMESPACE + fullyQualifiedName.Trim();

            Type type = Type.GetType(fullyQualifiedName);
            if (type != null)
            {
                return (IAttribute)Activator.CreateInstance(type);
            }

            foreach (var asm in AppDomain.CurrentDomain.GetAssemblies())
            {
                type = asm.GetType(fullyQualifiedName);
                if (type != null)
                {
                    return (IAttribute)Activator.CreateInstance(type);
                }
            }

            return null;
        }
    }
}
