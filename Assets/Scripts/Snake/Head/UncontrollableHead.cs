using System.Collections.Generic;
using UnityEngine;

public sealed class UncontrollableHead : IHeadMovement
{
    private readonly Transform head = null;

    private readonly List<Vector3> positionsHistory = null;
        
    private const int firstPositionInHistory = 0;

    public UncontrollableHead(List<Vector3> positionsHistory, Transform head)
    {
        this.head = head;
        this.positionsHistory = positionsHistory;
    }

    public void HeadMovement()
    {
        positionsHistory.Insert(firstPositionInHistory, head.position);
    }
}
