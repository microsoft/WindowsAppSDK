# 1. Workload Management

This feature provides APIs to manage a identify and manage a set of resources used collectively to
provide and perform a workload of activity.

- [1. Workload Management](#1-workload-management)

# 2. Background

Windows can provide a set of functionality via one or more MSIX packages and other resources. This
API provides the means to manage these related packages and resources as a higher level group of
functionality, called a 'workload'.

Microsoft-internal task [48267137](https://task.ms/48267137)

# 3. Description

This API supports managing workloads focusing on the following scenarios:

* Enumerate installed workloads
* Retrieve properties of a workload
* Remove installed packages and related resources comprising a workload

## 3.1. API Structure

## 3.2. Workload Definition via appxmanifest.xml

A workload has the following properties:

* Id -- programmatic identifier
* Rank -- prioritization for selection if multiple workloads have the same id
* DisplayName -- localizable name for user/human consumption
* Handler -- WinRT object providing operations manipulating the workload
* Supported Actions -- Operation(s) a  handler can perform

An MSIX package can define one or more workloads. The following manifest schema is used:

```xml
<Package>
  ...
  <Properties>
    <workload:Workloads>
      <Workload Id="id" Rank="rank" DisplayName="dn">
        <Actions ActivatableClassId="acid">
          <action/>
          ...
        </Actions>
      </Workload>
      ...
    </Workload:Workloads>
  </Properties>
  ...
</Package>
```

The following validations apply:

* Id (id)
  * String length: 1-255
  * Allowed characters: [A-Za-z0-9_.]
  * Comparison: Case-Insensitive (locale-invariant)
  * Occurrence: Required (minOccurs=maxOccurs=1)
  * Validation: Unique across all workloads in a package
* Rank (rank)
  * Int32
  * Occurrence: Required (minOccurs=maxOccurs=1)
* DisplayName (dn)
  * [Standard `DisplayName` definition](https://learn.microsoft.com/en-us/uwp/schemas/appxpackage/uapmanifestschema/element-displayname)
  * Occurrence: Required (minOccurs=maxOccurs=1)
* ActivatableClassId (acid)
  * [Standard `ActivatableClassId` definition](https://learn.microsoft.com/en-us/uwp/schemas/appxpackage/uapmanifestschema/element-activatableclass)
  * Occurrence: Optional (minOccurs=0, maxOccurs=1)
* Actions
  * Occurrence: Optional (minOccurs=0, maxOccurs=1)
* actions
  * The actions supported by this handler.
  * Occurrence: Required (minOccurs=maxOccurs=1).
  * NOTE: Currently only <Remove> is supported but other actions will be added in the future e.g. if a Repair action is supported expressing support for both Remove and Repair would be

```xml
        <Actions ActivatableClassId="acid">
          <Remove/>
          <Repair/>
        </Actions>
```

### 3.2.1. Workload 'Id' and Collisions

If packages are registered with multiple workloads containing the same `Id` then the workload with
the highest `Rank` is used. If multiple workloads have the same `Id` and `Rank` then they are
assumed to be equivalent and one will be used.

NOTE: This is the same collision management algorithm as used by Undocked Deployment Extension
Handlers (DEHs).

# 4. Examples

## 4.1. Remove all workloads

Fabrikam app removing all workloads.

```c#
namespace RemoveAllWorkloads
{
    static class Program
    {
        static void Main()
        {
            var workloadManager = WorkloadManager.GetDefault();
            foreach (string id in workloadManager.FindIds())
            {
                var workload = workloadManager.GetWorkload(id)
                if (workload.CanRemove())
                {
                    Console.Write($"Removing {workload.DisplayName}...");
                    await workload.RemoveWorkloadAsync();
                    Console.WriteLine($"Gone!");
                }
                else
                {
                    Console.Write($"{workload.DisplayName} does not support Remove");
                }
            }
        }
    }
}
```

# 5. Remarks

## 5.1. Platform Support

This API is only available on Windows >= 10.0.19041.0 (aka 2004 aka 20H1).

# 6. API Details

```c# (but really MIDL3)
namespace Microsoft.Windows.System.Workloads
{
    [contractversion(1)]
    apicontract WorkloadsContract{};

    [contract(WorkloadsContract, 1)]
    enum WorkloadStatus
    {
        InProgress = 0,         // The request is in progress
        CompletedSuccess = 1,   // The request completed successfully
        CompletedFailure = 2,   // The request failed with some critical internal error.
                                // See ExtendedError for HRESULT
    };

    [contract(WorkloadsContract, 1)]
    runtimeclass WorkloadResult
    {
        WorkloadStatus Status { get; };
        HRESULT ExtendedError { get; };
    }

    [contract(WorkloadsContract, 1)]
    enum WorkloadProgressStatus
    {
        Queued = 0,             // The request is queued
        InProgress = 1,         // The request is in progress
        CompletedSuccess = 2,   // The request completed successfully
        CompletedFailure = 3,   // The request failed with a critical internal error
                                // See ExtendedError for HRESULT
    };

    [contract(WorkloadsContract, 1)]
    struct WorkloadProgress
    {
        WorkloadProgressStatus Status;
        Double Progress;
    }

    [contract(WorkloadsContract, 1)]
    interface IWorkloadHandler
    {
        /// Remove the workload
        Windows.Foundation.IAsyncOperationWithProgress<WorkloadResult, WorkloadProgress>
        RemoveWorkloadAsync();
    }

    [contract(WorkloadsContract, 1)]
    runtimeclass Workload
    {
        /// Return the Id for all workloads
        static IVector<String> FindIds();

        /// Return a workload
        static Workload GetWorkload(String id);

        /// Return the unique identifier for this workload
        String Id { get; };

        /// Return the localized display name for this workload
        String DisplayName { get; };

        /// Return true if the workload supports Remove.
        Boolean CanRemove();

        /// Remove the workload
        Windows.Foundation.IAsyncOperationWithProgress<WorkloadResult, WorkloadProgress>
        RemoveWorkloadAsync();
    }
}
```
